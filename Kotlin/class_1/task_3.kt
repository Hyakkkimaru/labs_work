fun main() {
    println("Введите число от 1 до 5:")
    val number = readLine()?.toIntOrNull() ?: 0

    when (number) {
        1 -> println("один")
        2 -> println("два")
        3 -> println("три")
        4 -> println("четыре")
        5 -> println("пять")
        else -> println("ошибка")
    }
}
