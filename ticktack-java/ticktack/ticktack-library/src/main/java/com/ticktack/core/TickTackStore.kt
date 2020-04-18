package com.ticktack.core

import java.io.Closeable
import java.lang.Exception

/**
 * The TickTack store
 *
 * It provides access to the methods within
 */
class TickTackStore private constructor(configuration: TickTackStoreConfiguration) : Closeable {
  private var valid = true

  init {
    System.loadLibrary("ticktack_jni_lib")
  }

  private var handler: Long

  init {
    handler = open(configuration.path.toString())
  }

  companion object {
    private var counterMap: MutableMap<String, MutableList<Counter>> = mutableMapOf();

    private var counterStore: TickTackStore? = null

    /**
     * Sets the configuration of the default instance
     *
     * @param configuration
     */
    fun setConfiguration(configuration: TickTackStoreConfiguration) {
      this.counterStore = TickTackStore(configuration)
    }

    /**
     * Gets the default TickTack store
     */
    fun getDefaultInstance(): TickTackStore? {
      return counterStore
    }

    @JvmStatic
    fun onDataChange(key: String, value: Long) {
      for (counter in counterMap[key]!!)
        counter.notifyChange(value)
    }
  }

  /**
   * Returns an existing Counter or creates a new one
   *
   * @param key key of the Counter to retrieve
   * @throws Exception not valid store if the store was closed
   */
  fun getOrCreate(key: String): Counter {
    if(!valid) throw Exception("Not valid store")

    val counter = Counter(this, getOrCreate(handler, key), key)

    if (key !in counterMap)
      counterMap[key] = mutableListOf()

    counterMap[key]!!.add(counter)

    return counter
  }

  /**
   * Removes any data from disk
   */
  internal fun remove() = remove(handler)

  /**
   * Closes the store deleting any listener
   */
  override fun close() {
    valid = false

    for ((key, list) in counterMap) {
      for (counter in list){
          counter.valid = false
      }
    }

    close(handler)

    counterStore = null
  }

  internal fun removeCounter(counter: Counter) {
    with(counterMap[counter.key]?.iterator()){
      this?.forEach {
          if (it == counter) {
            remove()
          }
      }
    }
  }

  private external fun open(path: String): Long

  private external fun remove(handler: Long)

  private external fun getOrCreate(handler: Long, key: String): Long

  private external fun close(handler: Long)

}
