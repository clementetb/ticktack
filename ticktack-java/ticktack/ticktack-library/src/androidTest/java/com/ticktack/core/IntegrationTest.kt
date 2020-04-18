package com.ticktack.core

import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.platform.app.InstrumentationRegistry
import org.junit.*
import org.junit.Assert.assertEquals
import org.junit.runner.RunWith

/**
 * Instrumented ticktack-library, which will execute on an Android device.
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
@RunWith(AndroidJUnit4::class)
class IntegrationTest {
  companion object {
    private lateinit var tickTackStore: TickTackStore

    @JvmStatic
    @BeforeClass
    fun before(){
      val appContext = InstrumentationRegistry.getInstrumentation().targetContext

      TickTackStore.setConfiguration(
        TickTackStoreConfiguration.Builder()
          .name("test_db1")
          .build(appContext)
      )

      tickTackStore = TickTackStore.getDefaultInstance()!!
    }

    @JvmStatic
    @AfterClass
    fun after(){
      tickTackStore.remove()
    }
  }

  @Test
  fun testWriteTo10() {
    var counter = tickTackStore.getOrCreate("write10")

    for (i in 1..10)
      counter++

    assertEquals(10, counter.getValue())

  }

  fun write(count: Int, c: Counter) {
    var counter = c

    for (i in 1..count)
      counter++
  }

  @Test
  fun testWriteMultithreadedSameObject() {
    var counter = tickTackStore.getOrCreate("multiSame")

    val thread1 = Thread { write(50000, counter) }
    val thread2 = Thread { write(50000, counter) }

    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()

    assertEquals(100000, counter.getValue())
  }

  @Test
  fun testWriteMultithreadedDifferentObject() {
    var counter1 = tickTackStore.getOrCreate("multiDiff")
    var counter2 = tickTackStore.getOrCreate("multiDiff")

    val thread1 = Thread { write(50000, counter1) }
    val thread2 = Thread { write(50000, counter2) }

    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()

    assertEquals(100000, counter1.getValue())
    assertEquals(100000, counter2.getValue())
  }

  @Test
  fun testListeners() {
    var counter = tickTackStore.getOrCreate("listeners")
    var set = false;

    counter.addListener(object : Counter.ChangeListener{
      override fun onValueChanged(value: Long) {
        assertEquals(0, value)
        set = true
      }
    })

    assert(set)
  }
}
