# HTTP-Server

A simple http server.

Clients make HTTP requests to servers.
Servers respond to a client's HTTP request.

1. When requesting a file via HTTP, clients must provide the file's URL.
2. The web server must answer every HTTP request, at least with an error message.
3. On a web server, the HTTP server is responsible for processing and answering incoming requests.
4. Upon receiving a request, an HTTP server checks if the requested URL matches an existing file.

   a- If so, the web server sends the file content back to the browser. If not, the server will check if it should generate a file dynamically for the request (see Static vs. dynamic content).

   b- If neither of these options are possible, the web server returns an error message to the browser, most commonly 404 Not Found. The 404 error is so common that some web designers devote considerable time and effort to designing 404 error pages.

SOURCE: (https://developer.mozilla.org/en-US/docs/Learn_web_development/Howto/Web_mechanics/What_is_a_web_server)
