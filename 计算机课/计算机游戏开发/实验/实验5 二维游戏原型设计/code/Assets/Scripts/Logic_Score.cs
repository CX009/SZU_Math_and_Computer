using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class Logic_Score : MonoBehaviour {
    static int currentScore;  // ��ǰ�÷�
    static int highScore;  // ��ʷ��ߵ÷�

    public static int GetCurrentScore() {
        return currentScore;
    }

    public static int GetHighScore() {
        return highScore;
    }

    static TMP_Text GetCurrentScoreText() {
        return GameObject.Find("CurrentScore").GetComponent<TMP_Text>();
    }

    static TMP_Text GetHighScoreText()
    {
        return GameObject.Find("HighScore").GetComponent<TMP_Text>();
    }

    public static void UpdateCurrentScore(int _currentScore) {
        currentScore = _currentScore;

        TMP_Text currentScoreText = GetCurrentScoreText();
        currentScoreText.text = "Current Score: " + currentScore.ToString();
    }

    public static void UpdateHighScore(int _highScore) {
        highScore = _highScore;
        PlayerPrefs.SetInt("HighScore", highScore);

        TMP_Text highScoreText = GetHighScoreText();
        if (highScoreText != null) {
            highScoreText.text = "High Score: " + highScore.ToString();
        }
    }

    void Start() {
        // ��ʼ�� CurrentScore
        UpdateCurrentScore(0);

        // ��ʼ�� HighScore
        highScore = 0;
        if (PlayerPrefs.HasKey("HighScore")) {
            highScore = PlayerPrefs.GetInt("HighScore");
        }
        UpdateHighScore(highScore);
    }
}
