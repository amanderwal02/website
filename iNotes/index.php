<?php

    error_reporting(E_ALL);
    ini_set('display_errors', 1);

    //error_reporting(0);
    session_start();
    $date = date('Y-m-d'); 

    if(!isset($_SESSION['useremail'])){
        if(!isset($_SESSION['userpass'])){
            echo '<script>alert("Please login......")</script>';
            $url = "loginSignup.php";
            echo"<meta http-equiv='refresh' content='0;url=$url'>";
            return;
        }
    } else {
        $session = $_SESSION['useremail'];
        $session2 = $_SESSION['userpass'];
    }

?>

<?php

    $servername = "localhost";
    $username = "root";
    $pass = "";
    $database = "inotes";

    $conn = mysqli_connect( $servername , $username , $pass , $database );

    if ( !$conn ){
        die("Connection failed: " . mysqli_connect_error());
    }

    $table = str_replace('.', '_', $session);
    $sql = "SHOW TABLES LIKE '$table'";
    $result2 = mysqli_query($conn , $sql);
    $tableExist = false;
    $row = mysqli_num_rows($result2);
    if( $row > 0 ){
        $tableExist = true;
    }

    if( !($tableExist) ){
        $sql = "CREATE TABLE `$table` ( `s.no.` INT(11) NOT NULL AUTO_INCREMENT , `title` VARCHAR(100) NOT NULL , `description` TEXT NOT NULL , `tstamp` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP , PRIMARY KEY(`s.no.`))";
        mysqli_query($conn , $sql);
    }

?>

<?php

    $insert = false;
    $update = false;
    $delete = false;

    if(isset($_GET['delete'])){
        $sno = $_GET['delete'];
        $sql = "DELETE FROM `$table` WHERE `s.no.` = $sno";
        $result = mysqli_query($conn, $sql);
        if($result){
            $delete = true;
        }
    }

    $method = $_SERVER['REQUEST_METHOD'];
    
    if( $method == 'POST' ){
      
        if (isset( $_POST['snoEdit'])){
            $sno = $_POST["snoEdit"];
            $title = $_POST["titleEdit"];
            $description = $_POST["descriptionEdit"];
          
            $sql = "UPDATE `$table` SET `title` = '$title' , `description` = '$description' WHERE `$table`.`s.no.` = $sno";
            $result = mysqli_query($conn, $sql);
            if($result){
              $update = true;
            }
        } else {
            $title = $_POST['titles'];
            $description = $_POST['descs'];
      
            $sql = "INSERT INTO `$table` ( `title` , `description` ) VALUES ( '$title' , '$description' )";
            $result = mysqli_query( $conn , $sql );
            if($result){
                $insert = true;
            } 
        }
    
    }
      
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <title>iNOTES - PHP Curd</title>
        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <!-- Bootstrap CSS -->
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
        integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
        <link rel="stylesheet" href="//cdn.datatables.net/1.10.20/css/jquery.dataTables.min.css">
        <style>
            .colored-text {
                color: green;
            }

            .colored-text2 {
                color: blue; 
            }
        </style>
    </head>

    <body>

    <!-- Edit Modal -->
    <div class="modal fade" id="editModal" tabindex="-1" role="dialog" aria-labelledby="editModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="editModalLabel">Edit this Note</h5>
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">×</span>
                    </button>
                </div>

                <form action="index.php" method="POST">
                    <div class="modal-body">
                        <input type="hidden" name="snoEdit" id="snoEdit">
                        <div class="form-group">
                            <label for="title">Note Title</label>
                            <input type="text" class="form-control" id="titleEdit" name="titleEdit" aria-describedby="emailHelp">
                        </div>
                        <div class="form-group">
                            <label for="desc">Note Description</label>
                            <textarea class="form-control" id="descriptionEdit" name="descriptionEdit" rows="3"></textarea>
                        </div> 
                    </div>
                    <div class="modal-footer d-block mr-auto">
                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
                        <button type="submit" class="btn btn-primary">Save changes</button>
                    </div>
                </form>

            </div>
        </div>
    </div>

    <nav class="navbar navbar-expand-sm bg-dark">
        <ul class="navbar-nav">
            <li class="nav-item">
                <a class="nav-link" href="#">iNOTES</a>
            </li>
            <li class="nav-item">    
                <a class="nav-link" href="#">About</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="#">Contact Us</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="logout.php">Logout</a>
            </li>
        </ul>
    </nav>

    <?php
        if($insert){
            echo '<div class="alert alert-success alert-dismissible">
            <a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
            <strong>Success!</strong> Note Inserted Successfully.
            </div>';
            /*echo '<script>alert("Registeration done successfully......")</script>';*/
            $url = "index.php";
            echo"<meta http-equiv='refresh' content='0;url=$url'>";
        } 
    ?>
    <?php
        if($delete){
            echo "<div class='alert alert-success alert-dismissible fade show' role='alert'>
            <strong>Success!</strong> Your note has been deleted successfully
            <button type='button' class='close' data-dismiss='alert' aria-label='Close'>
            <span aria-hidden='true'>×</span>
            </button>
            </div>";
            $url = "index.php";
            echo"<meta http-equiv='refresh' content='0;url=$url'>";
        }
    ?>
    <?php
        if($update){
            echo "<div class='alert alert-success alert-dismissible fade show' role='alert'>
            <strong>Success!</strong> Your note has been updated successfully
            <button type='button' class='close' data-dismiss='alert' aria-label='Close'>
            <span aria-hidden='true'>×</span>
            </button>
            </div>";
            $url = "index.php";
            echo"<meta http-equiv='refresh' content='0;url=$url'>";
        }
    ?>
    <div class="container my-4">
        <div class = "container">
            <h2>Add a Note<br></h2>
            <div class="container my-3">
                <form id = "myForm" action="index.php" method = "post">
                    <div class="form-group">
                        <label for="text">Note Title</label>
                        <input type="text" name="titles" class="form-control" required placeholder="" id="titles">
                    </div>
                    <div class="form-group">
                        <label for="description">Note Description</label>
                        <textarea class = "form-control" required placeholder="" id = "descs" name = "descs" rows = "3"></textarea>
                    </div>
                    <button type="submit" class="btn btn-primary">Add Note</button>
                </form>
            </div>

        </div>
    </div>
    <br>
    <div class="container">
        <div class ="container">  
            <div class="container">          
                <table class="table table-striped" id="myTable">
                    <thead>
                        <tr>
                            <th>S.No.</th>
                            <th>Title</th>
                            <th>Description</th>
                            <th>Actions</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                            $sql = "SELECT * FROM `$table`";
                            $result = mysqli_query( $conn , $sql );
                            $sno = 1;
                            while( $row = mysqli_fetch_assoc($result) ){
                                if( ($sno % 2) == 0 ){
                                    echo "<tr>
                                    <th class='colored-text' scope='row'>". $sno . "</th>
                                    <td class='colored-text'>" . $row['title'] . "</td>
                                    <td class='colored-text'>" . $row['description'] . "</td>
                                    <td class='colored-text'><button class='edit btn btn-sm btn-primary' id=".$row['s.no.'].">Edit</button> <button class='delete btn btn-sm btn-primary' id=d".$row['s.no.'].">Delete</button></td>
                                    </tr>";
                                } else {
                                    echo "<tr>
                                    <th class='colored-text2' scope='row'>". $sno . "</th>
                                    <td class='colored-text2'>" . $row['title'] . "</td>
                                    <td class='colored-text2'>" . $row['description'] . "</td>
                                    <td class='colored-text2'><button class='edit btn btn-sm btn-primary' id=".$row['s.no.'].">Edit</button> <button class='delete btn btn-sm btn-primary' id=d".$row['s.no.'].">Delete</button></td>
                                    </tr>";
                                }
                                $sno++;
                            }
                        ?>
                    </tbody>
                </table>
            </div>
        </div>
    </div>
    <hr>
    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js"
        integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n"
        crossorigin="anonymous">
    </script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js"
        integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo"
        crossorigin="anonymous">
    </script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"
        integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6"
        crossorigin="anonymous">
    </script>
    <script src="//cdn.datatables.net/1.10.20/js/jquery.dataTables.min.js"></script>
    <script>
        $(document).ready(function () {
        $('#myTable').DataTable();
        });
    </script>
    <script>
        edits = document.getElementsByClassName('edit');
        Array.from(edits).forEach((element) => {
            element.addEventListener("click", (e) => {
                console.log("edit ");
                tr = e.target.parentNode.parentNode;
                title = tr.getElementsByTagName("td")[0].innerText;
                description = tr.getElementsByTagName("td")[1].innerText;
                console.log(title, description);
                titleEdit.value = title;
                descriptionEdit.value = description;
                snoEdit.value = e.target.id;
                console.log(e.target.id)
                $('#editModal').modal('toggle');
            })
        })

        deletes = document.getElementsByClassName('delete');
        Array.from(deletes).forEach((element) => {
            element.addEventListener("click", (e) => {
                console.log("edit ");
                sno = e.target.id.substr(1);
                if (confirm("Are you sure you want to delete this note!")) {
                    console.log("yes");
                    window.location = `index.php?delete=${sno}`;
                    // TODO: Create a form and use post request to submit a form
                }
                else {
                    console.log("no");
                }
            })
        })
    </script>

    </body>

</html>

