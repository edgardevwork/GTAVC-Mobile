package com.rockstargames.gtavc

import android.Manifest
import android.Manifest.permission.WRITE_EXTERNAL_STORAGE
import android.provider.Settings
import android.content.Intent
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat

class PermissionStorage : AppCompatActivity() {

    private val REQUEST_CODE_PERMISSIONS = 100
    private lateinit var btnGrantPermissions: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_permission_storage)

        btnGrantPermissions = findViewById(R.id.btn_grant_permissions)

        // Сначала проверяем наличие нужного разрешения
        checkAndHandlePermissions()
    }

    // Проверяем наличие разрешений и обрабатываем ситуацию
    private fun checkAndHandlePermissions() {
        if (hasWriteExternalStoragePermission()) { // Уже есть разрешение
            startGTAVCJava() // Переход к необходимой активности
        } else {
            // Нет разрешения, показываем кнопку для запроса
            btnGrantPermissions.visibility = View.VISIBLE
            btnGrantPermissions.setOnClickListener {
                requestPermissions()
            }
        }
    }

    // Проверяем наличие нужных разрешений
    private fun hasWriteExternalStoragePermission(): Boolean {
        return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            // Для Android 11 и выше используем новую концепцию Scoped Storage
            Environment.isExternalStorageManager()
        } else {
            // Для более ранних версий проверяем старое разрешение WRITE_EXTERNAL_STORAGE
            ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED
        }
    }
    // Запрашиваем необходимое разрешение
    private fun requestPermissions() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            if (!Environment.isExternalStorageManager()) {
                val intent = Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION).setData(
                    Uri.parse("package:${this.packageName}"))
                startActivity(intent)
            }
        } else {
        // Для Android 10 и ниже обычный запрос разрешений
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE), REQUEST_CODE_PERMISSIONS)
        }
    }

    // Обработчик результатов запросов разрешений
    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        when (requestCode) {
            REQUEST_CODE_PERMISSIONS -> {
                if ((grantResults.isNotEmpty() &&
                            grantResults[0] == PackageManager.PERMISSION_GRANTED)) {
                    startGTAVCJava()
                } else {
                    showErrorMessage("Разрешение на доступ к хранилищу отказано.")
                }
            }
        }
    }

    // Запуск активности GTAVC.java
    private fun startGTAVCJava() {
        try {
            val intent = Intent(this, GTAVC::class.java)
            startActivity(intent)
        } catch (ex: Exception) {
            ex.printStackTrace()
            Log.e("PermissionStorage", "Ошибка при запуске GTAVC: ${ex.message}")
        }
    }

    // Вспомогательная функция для вывода сообщений
    private fun showErrorMessage(message: String) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show()
    }
}