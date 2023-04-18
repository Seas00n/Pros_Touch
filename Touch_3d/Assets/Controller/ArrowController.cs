using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrowController : MonoBehaviour
{
    public GameObject target;
    private float rotate_speed = 10;
    private float long_speed = 4;
    private Vector3 rotate_axis = new Vector3(0, 0, 1);
    private float current_angle = 0;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void LateUpdate()
    {
        transform.position = target.transform.position;
        transform.localScale+=new Vector3(0,0,Time.deltaTime*long_speed);
        current_angle = Time.deltaTime * rotate_speed;
        transform.RotateAround(target.transform.position, rotate_axis, current_angle);
        
    }
}
