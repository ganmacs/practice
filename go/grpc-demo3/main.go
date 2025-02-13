package main

import (
	"log"
	"os"
	"time"

	"golang.org/x/net/context"
	"google.golang.org/grpc"
	pb "google.golang.org/grpc/health/grpc_health_v1"
)

const (
	address     = "localhost:8000"
	defaultName = "hello"
)

func main() {
	// Set up a connection to the server.
	conn, err := grpc.Dial(address, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	c := pb.NewHealthClient(conn)

	// Contact the server and print out its response.
	name := defaultName
	if len(os.Args) > 1 {
		name = os.Args[1]
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()
	r, err := c.Check(ctx, &pb.HealthCheckRequest{Service: name})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}

	log.Printf("healthcheck: %s", r.Status)
}
