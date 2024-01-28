fun main() {
  val number1 = readLine()?.toIntOrNull() ?: 0
  val number2 = readLine()?.toIntOrNull() ?: 0

  when {
    number1 > number2 -> println("первое число больше")
    number1 < number2 -> println("второе число больше")
    else -> println("числа равны")
  }
}
