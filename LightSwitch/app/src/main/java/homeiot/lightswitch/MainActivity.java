package homeiot.lightswitch;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnLightSwitch = findViewById(R.id.btnStartLightSwitch);
        btnLightSwitch.setOnClickListener(v -> {
            Intent intent = new Intent(getApplicationContext(), LightSwitchActivity.class);
            startActivity(intent);
        });
    }
}
