use std::io::{Read, Write};
use std::net::TcpStream;

fn main() {
    // Connects to the server.
    // Change the ip and port to the server one if you want changed it.
    let mut stream = TcpStream::connect("127.0.0.1:1234").expect("Failed to connect to server");
    let mut message = String::new();

    // Asks and reads user input
    print!("The flag is: ");
    std::io::stdout()
        .flush()
        .expect("Not able to flush the stdout.");
    match std::io::stdin().read_line(&mut message) {
        Ok(_) => (),
        Err(e) => eprintln!("Got the following error while getting user input: {}", e),
    }

    // Sends the input to the server
    stream
        .write(message.as_bytes())
        .expect("Failed to send data");

    // Gets and displays the server response
    let mut response = String::new();
    stream
        .read_to_string(&mut response)
        .expect("Failed to read server response");

    println!("Received: {}", response);
}
