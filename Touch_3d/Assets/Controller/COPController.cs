using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class COPController : MonoBehaviour
{
    public float origin_x = 0;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = new Vector3(origin_x, 0,0);
    }
}
