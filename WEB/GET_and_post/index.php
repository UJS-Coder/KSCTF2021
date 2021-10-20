<?php
$major = @$_GET['major'];
$key = @$_POST['key'];

if ($major == "sec" && !@md5($key)) {
    include "flag.php";
    echo $flag;
} else {
    highlight_file("./index.php");
    echo "</br>welcome_to_ctf have_fun";
}