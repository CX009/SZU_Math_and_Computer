using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using Unity.VisualScripting;
using TMPro;

public class Logic_EndScene : MonoBehaviour {
    static TMP_Text GetScoreText() {
        return GameObject.Find("Score").GetComponent<TMP_Text>();
    }

    void Start() {
        // ��ʾ��ǰ����
        int currentScore = Logic_Score.GetCurrentScore();
        Debug.Log(currentScore);
        Debug.Log(Logic_Score.GetHighScore());
        TMP_Text score = GetScoreText();
        score.text = currentScore.ToString();

        // �����Ƽ�¼ͼƬ
        GameObject breakRecord = GameObject.Find("BreakRecord");
        breakRecord.SetActive(false);

        // ���Ƽ�¼, ��ʾ�Ƽ�¼��ͼƬ, ������ HighScore
        if (currentScore > Logic_Score.GetHighScore()) {
            Debug.Log("Break");
            breakRecord.SetActive(true);
            Logic_Score.UpdateHighScore(currentScore);
        }
    }
}
