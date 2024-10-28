/**
 * @file example.cpp
 * @brief Пример класса с описанием методов
 */

/**
 * @class Example
 * @brief Пример класса с различными типами методов
 */
class Example {
public:
    /**
     * @brief Конструктор по умолчанию
     * Инициализирует атрибуты объекта значениями по умолчанию.
     */
    Example();

    /**
     * @brief Конструктор копирования
     * Создает новый объект, копируя атрибуты существующего объекта.
     * @param other Другой объект класса Example
     */
    Example(const Example& other);

    /**
     * @brief Деструктор
     * Освобождает ресурсы, выделенные объекту.
     */
    ~Example();

    /**
     * @brief Геттер для атрибута value
     * Возвращает значение атрибута value.
     * @return Значение атрибута value
     */
    int getValue() const;

    /**
     * @brief Сеттер для атрибута value
     * Изменяет значение атрибута value.
     * @param newValue Новое значение атрибута value
     */
    void setValue(int newValue);

    /**
     * @brief Метод-действие
     * Выполняет определенное действие с объектом.
     */
    void performAction();

    /**
     * @brief Статический метод
     * Выполняет операцию, не связанную с конкретным объектом.
     */
    static void staticMethod();

private:
    int value; ///< Атрибут класса
};