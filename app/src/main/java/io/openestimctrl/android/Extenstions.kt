package io.openestimctrl.android

inline infix fun <reified E : Enum<E>, V> ((E) -> V).findBy(value: V): E? {
    return enumValues<E>().firstOrNull { this(it) == value }
}

inline infix fun <reified E : Enum<E>, V> ((E) -> V).findOrThrowBy(value: V): E {
    return enumValues<E>().first { this(it) == value }
}