using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using Unity.VisualScripting;

public class Logic_Basket : MonoBehaviour {
    [Header("Set in Inspector")]
    public float xRange = 20.0f;
    GameObject soundEffectObject;
    GameObject appleTreeObject;

    void Start() {
        soundEffectObject = GameObject.Find("SoundEffectLogicObject");
        appleTreeObject = GameObject.Find("AppleTree");
    }

    void Update() {
        Vector3 mousePosition2D = Input.mousePosition;  // ������Ļ����

        // ������� z �����������ά�ռ��н������ z ����ǰ�ƶ���Զ
        mousePosition2D.z = -Camera.main.transform.position.z;

        // ���õ�ת��Ϊ��ά����������
        Vector3 mousePosition3D = Camera.main.ScreenToWorldPoint(mousePosition2D);

        // �޸������ x ����
        Vector3 position = this.transform.position;
        position.x = mousePosition3D.x;
        position.x = Mathf.Max(position.x, -xRange);
        position.x = Mathf.Min(position.x, xRange);
        this.transform.position = position;
    }

    void OnCollisionEnter(Collision collision) {
        // ����ײ����ƻ��, ������ƻ��
        GameObject collidedWith = collision.gameObject;
        if (collidedWith.tag == "Apple") {
            Destroy(collidedWith);

            // �� 1 ��
            Logic_Score.UpdateCurrentScore(Logic_Score.GetCurrentScore() + 1);

            // ������Ч
            soundEffectObject.GetComponent<AudioSource>().Play();

            // ƻ���������
            float timeInterval2DropApples = appleTreeObject.GetComponent<Logic_AppleTree>().timeInterval2DropApples;
            appleTreeObject.GetComponent<Logic_AppleTree>().timeInterval2DropApples = Mathf.Max(timeInterval2DropApples - 0.01f, 0.2f);
        }
    }
}
