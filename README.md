# VulnCheck - SAST анализатор кода на Python  

### **Приветствие**  
Спасибо, что уделили внимание моему проекту! VulnCheck - это статический анализатор кода (SAST) для Python, написанный на C++. Утилита предназначена для поиска уязвимостей в исходном коде с использованием предопределённых шаблонов.  

---  

## Установка и запуск  

### **Требования**  
- CMake ≥ 3.14  
- Компилятор с поддержкой C++20 (GCC, Clang, MSVC)  
- Git (для подмодулей)  

### **Сборка**  
1. Клонируйте репозиторий:  
   ```bash
   git clone https://github.com/ce-fello/VulnCheck.git
   cd vulncheck
   ```  
2. Инициализируйте подмодули:  
   ```bash
   git submodule update --init --recursive
   ```  
3. Соберите проект:  
   ```bash
   mkdir build && cd build
   cmake .. && make
   ```  

---  

## Использование  
После сборки запустите анализатор:  
```bash
./vulncheck <путь_к_python_файлу_или_папке> [-j | --json ] [--output=<путь_к_отчёту>] [ -r | --recursive]
```  

### **Аргументы**  
- `--output` – вывод отчёта в конкретный файл в формате JSON
- `--json | -j` – вывод отчёта (без флага `--output` сгенерирует в файл `report.json`)
- `--recurisve | -r` – анализ всех Python файлов в директории, а не только одного конкретного

### **Пример**  
```bash
./vulncheck /path/to/patterns_list /path/to/python/code -j --output /my/report.json --recursive
```  

---  

## Правила анализа  
Шаблоны уязвимостей хранятся в `patterns/vulnerabilities.yaml`. Но при желании вы можете написать собственный лист или изменить существующий. И при работе с утилитой указывать именно его. 
Формат:  
```yaml
- id: "python-eval"
  message: "Use of eval() is dangerous"
  pattern: "\\beval\\s*\\("
  type: regex
  severity: "high"
  tags: ["eval", "code-execution"]
```  

---  

## Тестирование  
Запуск тестов:  
```bash
cd build
ctest
```  
Или соберите и запустите тесты вручную:  
```bash
cd tests
cmake .. && make
./run_tests
```  

---  

## Структура проекта  
```  
vulncheck/
├── docs/              # Документация
├── external/          # Зависимости (doctest, json, yaml-cpp)
├── patterns/          # Встроенные YAML-шаблоны уязвимостей
├── src/               # Исходный код анализатора
├── test_service/      # Тестовые Python-сервисы
└── tests/             # Юнит-тесты на C++
```  

---  

## Примечания  
- Для добавления новых проверок редактируйте `vulnerabilities.yaml`.
- Поддерживается вывод в JSON через `JsonReportWriter`.

---  

### **Благодарности**  
Спасибо за просмотр этого проекта! Если у вас есть вопросы или предложения, буду рад обсудить. Надеюсь, код окажется полезным и понятным.
