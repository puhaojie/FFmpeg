package com.phj.player;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class PlayActivity extends AppCompatActivity {
    private Button btfile;
    private Button btrtmp;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);

        btfile = (Button) findViewById( R.id.playvideo );
        btfile.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        EditText t = (EditText) findViewById( R.id.fileurl );
                        //用户输入的URL，打开视频
                        Open(t.getText().toString());

                        //关闭当前窗口
                        finish();
                    }
                }
        );


        btrtmp = (Button) findViewById( R.id.playrtmp );
        btrtmp.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        EditText t = (EditText) findViewById( R.id.rtmpurl );
                        //用户输入的URL，打开视频
                        Open(t.getText().toString());

                        //关闭当前窗口
                        finish();
                    }
                }
        );

    }
    public native void Open(String url);

}
