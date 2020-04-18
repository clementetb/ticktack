package com.ticktack.buttoncounter

import android.view.View
import androidx.databinding.BaseObservable
import androidx.databinding.Bindable
import com.ticktack.core.Counter
import java.util.*

class CounterViewModel(private var counter: Counter, startTimer: Boolean) : BaseObservable() {
  private var timer: Timer? = null

  @get:Bindable
  var ticks: String = counter.getValue().toString()

  init {
    counter.addListener(object : Counter.ChangeListener {
      override fun onValueChanged(value: Long) = setTicks(value)
    })

    if (startTimer) onToggleTimer(null)
  }

  fun setTicks(value: Long) {
    ticks = value.toString()
    notifyPropertyChanged(BR.ticks)
  }

  fun onToggleTimer(v: View?) {
    if (timer == null) {
      timer = Timer("Counter timer")
      timer?.schedule(object : TimerTask() {
        override fun run() {
          counter++
        }
      }, 0, 1000)
    } else {
      timer?.cancel()
      timer = null
    }
  }

  fun onIncrementCounter(v: View) {
    counter++
  }

  fun isTimerOn() = timer != null

  fun stopTimer() = timer?.cancel()
}
