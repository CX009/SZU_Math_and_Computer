using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using Unity.VisualScripting;

public class Logic_AppleTree : MonoBehaviour {
    [Header("Set in Inspector")]
    // ƻ�������ƶ�
    public float moveSpeed = 10.0f;  // ƻ�����ƶ��ٶ� (��λ / ��)
    public float xRange = 20.0f;  // ƻ�����ƶ���ΧΪ ��leftAndRightEdge
    public float probability2SwitchDirection = 0.02f;  // ƻ����ת��ĸ���

    // ƻ��������ƻ��
    public GameObject applePrefab;  // ƻ��Ԥ����
    public float delay2DropFirstApple = 1.0f;  // �����һ��ƻ����ʱ����
    public float timeInterval2DropApples = 0.8f;  // ����һ��ƻ����, ����ƻ����ʱ����
    
    void Start() {
        // InvokeRepeating("DropApple", delay2DropFirstApple, timeInterval2DropApples);
        Invoke("DropApple", delay2DropFirstApple);
    }

    void DropApple() {
        GameObject apple = Instantiate<GameObject>(applePrefab);
        apple.transform.position = transform.position;

        Invoke("DropApple", timeInterval2DropApples);
    }

    void Update() {
        transform.Translate(moveSpeed * Time.deltaTime, 0.0f, 0.0f);

        // �����߽�ת��
        float x = transform.position.x;
        if (x < -xRange || x > xRange) {
            moveSpeed = -moveSpeed;
        }
    }

    void FixedUpdate() {
        // 10% �ĸ���ת��
        if (Random.value < probability2SwitchDirection) {
            moveSpeed *= -1;
        }
    }
}
