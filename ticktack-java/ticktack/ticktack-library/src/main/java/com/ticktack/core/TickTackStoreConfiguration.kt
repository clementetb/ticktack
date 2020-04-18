package com.ticktack.core

import android.content.Context
import java.io.File

/**
 * This class is used by the TickTackStore to be configured
 *
 */
class TickTackStoreConfiguration private constructor(internal val path: File){
  data class Builder(internal var name: String? = "default"){
    /**
     * Sets the TickTack store to open
     */
    fun name(name: String) = apply { this.name = name }

    /**
     * Generates a configuration
     */
    fun build(context: Context) = TickTackStoreConfiguration(File(context.filesDir, "$name.cdb"))
  }
}
