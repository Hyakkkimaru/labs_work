fun sum(n: Int): Int {
    var sum = 0
    var num = n
    while (num > 0) {
        sum += num % 10
        num /= 10
    }
    return sum
}

fun main() {
    val n = 123
    val sum = sum(n)
    println("Сумма чисел: $sum")
}
