using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using Unity.VisualScripting;

public class Logic_StartButton : MonoBehaviour {
    public void StartButtonClicked() {
        // ��ʼ��Ϸ
        SceneManager.LoadScene("GameScene");
    }
}
