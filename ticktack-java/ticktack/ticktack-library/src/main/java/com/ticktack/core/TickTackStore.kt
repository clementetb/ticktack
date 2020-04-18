package com.ticktack.core

/**
 * The TickTack store
 *
 * It provides access to the methods within
 */
class TickTackStore private constructor(configuration: TickTackStoreConfiguration) {
  init {
    System.loadLibrary("ticktack_jni_lib")
  }

  private var handler: Long

  init {
    handler = open(configuration.path.toString())
  }

  companion object {
    private var counterMap: MutableMap<String, MutableList<Counter>> = mutableMapOf();

    private lateinit var counterStore: TickTackStore

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
    fun getDefaultInstance(): TickTackStore {
      return counterStore
    }

    @JvmStatic
    internal fun onDataChange(key: String, value: Long) {
        for (counter in counterMap[key]!!)
          counter.notifyChange(value)
    }
  }

  /**
   * Returns an existing Counter or creates a new one
   *
   * @param key key of the Counter to retrieve
   */
  fun getOrCreate(key: String): Counter {
    val counter = Counter(getOrCreate(handler, key))

    if (key !in counterMap)
      counterMap[key] = mutableListOf()

    counterMap[key]!!.add(counter)

    return counter
  }

  /**
   * Removes any data from disk
   */
  internal fun remove() = remove(handler)

  private external fun open(path: String): Long

  private external fun remove(handler: Long)

  private external fun getOrCreate(handler: Long, key: String): Long

}
