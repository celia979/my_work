using UnityEngine;

public class player : MonoBehaviour
{
    public float moveSpeed = 5f;
    public float jumpForce = 10f;
    private bool isGrounded;
    private Rigidbody2D rb;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.P))
        {
            print("Hello World");
       }
       
       // Handle horizontal movement
        float moveInput_x = Input.GetAxis("Horizontal");
        float moveInput_y = Input.GetAxisRaw("Vertical");
        rb.linearVelocity = new Vector2(moveInput_x * moveSpeed, moveInput_y * moveSpeed);

        // Handle jumping
        if (Input.GetButtonDown("Jump") && isGrounded)
        {
            rb.linearVelocity = new Vector1(rb.linearVelocity.x, jumpForce);
        }
    }

/*    void OnEnterCollision2D(collision2D other)
    {
        if (other.CompareTag("Grounded")) {
            isGrounded = true;
        }
    }

    void OnExitCollision2D(collision2D other)
    {
        if (other.CompareTag("Grounded")) {
            isGrounded = false;
        }
    }*/
}
