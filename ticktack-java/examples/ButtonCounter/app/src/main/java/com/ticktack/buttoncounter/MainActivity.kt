package com.ticktack.buttoncounter

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.ticktack.buttoncounter.databinding.ActivityMainBinding
import com.ticktack.core.TickTackStore
import com.ticktack.core.TickTackStoreConfiguration

class MainActivity : AppCompatActivity() {
  companion object {
    const val TIMER_ON = "TIMER_ON"
  }

  private lateinit var binding: ActivityMainBinding
  private var tickTackStore : TickTackStore? = null

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)
    setContentView(R.layout.activity_main)

    TickTackStore.setConfiguration(TickTackStoreConfiguration.Builder().name("my_test").build(this))
    tickTackStore = TickTackStore.getDefaultInstance()

    if(tickTackStore== null) return

    binding = DataBindingUtil.setContentView(this, R.layout.activity_main)
    binding.viewmodel = CounterViewModel(
      tickTackStore!!.getOrCreate("my_counter"),
      savedInstanceState?.getBoolean(TIMER_ON, false) ?: false
      )
  }

  override fun onSaveInstanceState(outState: Bundle) {
    super.onSaveInstanceState(outState)
    outState.putBoolean(TIMER_ON, binding.viewmodel!!.isTimerOn())
  }

  override fun onDestroy() {
    super.onDestroy()
    binding.viewmodel?.stopTimer()

    tickTackStore?.close()
  }
}
