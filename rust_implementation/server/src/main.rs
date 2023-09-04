use std::io::{BufRead, BufReader, Write};
use std::net::{Shutdown, TcpListener};

fn main() {
    // Define the tcp listener for the socket.
    // Change the ip inside the bind if you want to.
    let listener = TcpListener::bind("127.0.0.1:1234").expect("Error while binding the socket.");
    // Make the tcp listener work.
    for stream in listener.incoming() {
        let mut tcp_stream = stream.expect("Error while starting the tcp stream.");
        let mut reader = BufReader::new(&tcp_stream);
        let mut line = String::new();

        // Takes user input and checks if it is right
        if reader.read_line(&mut line).is_ok() {
            let flag = line.trim();
            if flag == "ovo" {
                match tcp_stream.write_all(b"uabo\n") {
                    Ok(_) => (),
                    Err(e) => eprintln!("Error sending message to the client: {}", e),
                }
            } else {
                match tcp_stream.write_all(b"You failed L bozo\n") {
                    Ok(_) => (),
                    Err(e) => eprintln!("Error sending message to the cleint: {}", e),
                }
            };
            tcp_stream.flush().expect("Error flushing the tcp stream.");
        }

        // Gracefully terminate all the socket operations, closes it and waits for other.
        match tcp_stream.shutdown(Shutdown::Both) {
            Ok(_) => drop(tcp_stream),
            Err(_) => drop(tcp_stream),
        }
    }
}
