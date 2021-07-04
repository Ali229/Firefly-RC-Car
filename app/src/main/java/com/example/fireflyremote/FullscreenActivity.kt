package com.example.fireflyremote

import android.R.attr.*
import android.annotation.SuppressLint
import android.os.Bundle
import android.view.MotionEvent
import android.view.View
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.fireflyremote.databinding.ActivityFullscreenBinding


class FullscreenActivity : AppCompatActivity() {

    private lateinit var binding: ActivityFullscreenBinding
    private lateinit var fullscreenContent: TextView
    lateinit var imageView: ImageView
    var pDownX = 0f
    var pDownY = 0f
    var pUpX = 0
    var pUpY = 0

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityFullscreenBinding.inflate(layoutInflater)
        setContentView(binding.root)

        fullscreenContent = binding.fullscreenContent
        fullscreenContent.systemUiVisibility =
            View.SYSTEM_UI_FLAG_LOW_PROFILE or
                    View.SYSTEM_UI_FLAG_FULLSCREEN or
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE or
                    View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY or
                    View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION or
                    View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
        imageView = findViewById(R.id.imageView5)
        imageView.setOnTouchListener { v, event ->
            val action = event.action
            when (action) {

                MotionEvent.ACTION_DOWN -> {
                    pDownY = event.y
                    imageView.rotationY = pDownY
                    true
                }
                else -> {
                    false
                }
            }
        }

    }

}