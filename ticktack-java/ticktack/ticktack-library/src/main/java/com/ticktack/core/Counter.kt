package com.ticktack.core

/**
 * A Counter, it keeps track of the ticks and tacks
 */
class Counter internal constructor(private val handler: Long) {
  interface ChangeListener {
    fun onValueChanged(value: Long)
  }

  private val listenerList = mutableListOf<ChangeListener>()

  /**
   * Increments the counter by one
   */
  operator fun inc(): Counter {
    increment(handler)
    return this
  }

  /**
   * Returns the current counter value
   *
   * @return The value as long
   */
  fun getValue(): Long = getValue(handler)

  /**
   * Adds a listener that will receive notifications when there is an update
   *
   * @param listener
   */
  fun addListener(listener: ChangeListener) = listenerList.add(listener)

  /**
   * Removes any further notifications to a listener
   *
   * @param listener
   */
  fun removeListener(listener: ChangeListener) {
    with(listenerList.iterator()){
      forEach {
        if (it == listener)
          remove()
      }
    }
  }

  internal fun notifyChange(value: Long) {
    with(listenerList.iterator()){
      forEach {
        it.onValueChanged(value)
      }
    }
  }

  private external fun increment(handler: Long): Long

  private external fun getValue(handler: Long): Long
}
