{
  "version": "0.0.1",
  "configurations": [
    {
      "name": "cyberhub-preview",
      "runtimeExecutable": "perl",
      "runtimeArgs": [
        "-MIO::Socket::INET",
        "-e",
        "use IO::Socket::INET; use POSIX; my $srv=IO::Socket::INET->new(LocalPort=>3000,Type=>SOCK_STREAM,Reuse=>1,Listen=>10) or die $!; while(my $c=$srv->accept){my $req=''; while(my $l=<$c>){$req.=$l;last if $l eq \"\\r\\n\"} my $file='C:/Users/gensh/CyberHub/preview.html'; open(my $f,'<',$file) or do{print $c \"HTTP/1.1 404 Not Found\\r\\n\\r\\n\";close $c;next}; my $body=do{local $/;<$f>}; close $f; my $len=length($body); print $c \"HTTP/1.1 200 OK\\r\\nContent-Type: text/html; charset=utf-8\\r\\nContent-Length: $len\\r\\n\\r\\n$body\"; close $c}"
      ],
      "port": 3000
    }
  ]
}
