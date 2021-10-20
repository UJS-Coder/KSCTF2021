<?php

if(isset($_GET['c'])){
    $c = $_GET['c'];
    if($c==='flag')
    {
        system('cat flag.php');
    }
}else{
    highlight_file(__FILE__);
}
?>