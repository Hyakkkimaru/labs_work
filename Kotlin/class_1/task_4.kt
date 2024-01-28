fun check(email: String, password: String): String {
    if (!email.contains("@") || !email.contains(".")) {
        return "Неправильный формат почты. Проверьте и введите снова."
    }

    if (password.length < 7 || !password.any { it.isDigit() } || !password.any { it.isUpperCase() }) {
        return "Пароль должен быть длиной не менее 6 символов, содержать хотя бы одну цифру и одну заглавную букву. Пожалуйста проверьте и попробуйте снова."
    }

    return "Почта и пароль верны."
}

fun main() {
    val email = "test@gmail.com"
    val password = "123456Е"

    println(check(email, password))
}
