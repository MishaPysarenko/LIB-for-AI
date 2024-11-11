import argparse
import subprocess
from datetime import datetime

def parse_network_description(network_description):
    lines = network_description.strip().split('\n')
    
    # 1. Тип открытия и архитектура (не используется в PlantUML, но можно сохранить для дальнейшего использования)
    opening_type = lines[0]
    architecture_type = lines[1]
    
    # 2. Количество слоев
    num_layers = int(lines[2])
    
    # 3. Обработка слоев и нейронов
    layers = {}
    index = 3  # Индекс начала описания слоев
    for layer in range(num_layers):
        layer_info = lines[index].split('-')
        num_neurons = int(layer_info[0])  # Число нейронов в слое
        activation_functions = [func for func in layer_info[1].split('.') if func]  # Парсинг функций активации, разделённых точкой
        
        # Проверка на соответствие количества функций активации количеству нейронов
        if len(activation_functions) < num_neurons:
            # Заполняем отсутствующие функции активации значением "None"
            activation_functions.extend(["None"] * (num_neurons - len(activation_functions)))
        
        # Сохраняем информацию о нейронах и их функциях активации
        layers[layer] = [(f"{layer}.{i}", activation_functions[i]) for i in range(num_neurons)]
        index += 1
    
    # 4. Обработка рёбер
    edges = []
    for edge_line in lines[index:]:
        source, target_weight = edge_line.split('=')
        source_neuron, target_neuron = source.split('-')
        weight = target_weight.strip()
        edges.append((source_neuron, target_neuron, weight))
    
    # Генерация сценария PlantUML
    uml_script = ["@startuml", "!define Neuron(name, activation) class name <<activation>> #LightBlue", ""]

    # Добавление входных нейронов
    for neuron_name, activation in layers[0]:
        uml_script.append(f"Neuron(I.{neuron_name.split('.')[1]}, \"{activation}\")")

    # Добавление промежуточных и выходных нейронов
    for layer, neurons in layers.items():
        if layer == 0:
            continue  # Пропустить входной слой
        for neuron_name, activation in neurons:
            if layer == num_layers - 1:
                # Последний слой — выходной
                uml_script.append(f"Neuron(O.{neuron_name.split('.')[1]}, \"{activation}\")")
            else:
                uml_script.append(f"Neuron({neuron_name}, \"{activation}\")")
    
    # Добавление рёбер
    uml_script.append("")  # Разделение для удобочитаемости
    for source, target, weight in edges:
        uml_script.append(f"{source} -> {target} : weight={weight}, edgeName={source}-{target}")
    
    uml_script.append("@enduml")
    return "\n".join(uml_script)


if __name__ == "__main__":
    # Создаем парсер командной строки
    parser = argparse.ArgumentParser(description='Считывание содержимого файла.')
    
    # Добавляем параметр для пути к файлу
    parser.add_argument('file', type=str, help='Путь к файлу, содержимое которого нужно считать')
    
    # Парсим аргументы
    args = parser.parse_args()
    
    with open(args.file, 'r') as file:
        # Считываем все содержимое файла в переменную
        content = file.read()



# Генерация UML сценария
uml_script = parse_network_description(content)

formatted_time = datetime.now().strftime("%H_%M_%S-%d_%m_%Y")

# Открываем файл на запись
with open(formatted_time + ".txt", "w") as file:
    file.write(uml_script)

name = formatted_time + ".txt"

subprocess.run(["java", "-jar", "plantuml.jar", name])