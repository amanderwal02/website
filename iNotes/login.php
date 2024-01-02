<?php

    /*error_reporting(E_ALL);
    ini_set('display_errors', 1);*/

    error_reporting(0);

    $database = "inotes";
    $username = "root";
    $server = "localhost";
    $pass = "";

    $passStatus = false;
    $emailStatus = false;

    $conn = mysqli_connect( $server , $username , $pass , $database );
    if( !($conn) ){
        die("Connection failed: " . mysqli_connect_error());
    }

    $method = $_SERVER['REQUEST_METHOD'];

    if( $method == 'POST'){

        if(isset($_POST['lemail'])){
            $userEmail = $_POST['lemail'];
            $userPassword = $_POST['lpass'];
        }

    }

    $sql = "SELECT * FROM `users`";
    $result = mysqli_query($conn , $sql);
    while( $row = mysqli_fetch_assoc($result) ){
        if($row['email'] == $userEmail){
            $emailStatus = true;
            if($row['pass'] == $userPassword){
                $passStatus = true;
            }
        }
    }

    $url = 'loginSignup.php';
    $postData = array(
        'lvEmail' => $userEmail , 'lvPass' => $userPassword , 'vemail' => $emailStatus , 'vpass' => $passStatus
    );

    echo "<form id='redirectForm' action='{$url}' method='post'>";
    foreach ($postData as $key => $value) {
        echo "<input type='hidden' name='{$key}' value='{$value}'>";
    }
    echo "</form>";
    echo "<script>document.getElementById('redirectForm').submit();</script>";
    exit();

?>