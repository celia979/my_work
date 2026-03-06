using UnityEngine;

public class enemy : MonoBehaviour
{
    public float moveSpeed = 5f;
    private Rigidbody2D rb;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    void Update()
    {
       float moveHorizontal = direction;

        Vector3 movement = new Vector3 (moveHorizontal, 0.0f);
        rigidbody2D.velocity = movement * speed;
    }

}
