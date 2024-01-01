<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="author" content="dead craft">
    <meta name="description" content="website | Web Developer | Open source Enthusiast">
    <meta name="keywords" content="Dead craft, Aman Derwal, portfolio, css, javascript, software, coding, programming, web, 
    development, developer, frontend">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="google-site-verification" content="IZ7Sm227j_9N0Sy_JmwOvn1_OAm_O2rHr2833ZV0Fro">
    <title>Dead Craft</title>
    <link rel= "stylesheet" href="style1.css" />
    <script src="https://kit.fontawesome.com/66aa7c98b3.js" crossorigin="anonymous"></script>
    <link href="https://fonts.googleapis.com/css?family=Comfortaa:400,700,300|Quattrocento" rel="stylesheet">
    <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap">
    <link rel="shortcut icon" href="./img/fbavatar_1630400663387_6838396024049256103.png" type="image/x-icon">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
    integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
    <meta name="title" content="Portfolio Website | Aman Derwal">
    <meta name="title" content="Portfolio Website | dead craft">
    <meta itemprop="description" content="Web Developer | Open source Enthusiast">
    <meta name="application-name" content="Website">
    <meta property="og:site_name" content="">
    <meta property="og:type" content="website">
    <meta property="og:url" content="https://sanketbodake.ninja/">
    <meta property="og:title" content="dead craft">
    <meta property="og:description" content="Portfolio website | Web Developer | Open source Enthusiast">
    <meta name="url" content="https://sanketbodake.ninja/">
    <meta name="language" content="English">  
    <meta property="twitter:card" content="summary_large_image">
    <meta name="twitter:url" content="https://sanketbodake.ninja/">
    <meta name="twitter:title" content="dead craft">
    <meta name="twitter:description" content="Portfolio website | Web Developer | Open source Enthusiast">
    <meta name="twitter:site" content="@Sanket46171296">
    <meta name="twitter:creator" content="@Sanket46171296">
    <meta name="url" content="https://sanketbodake.ninja/">
    <meta property="og:locale" content="en">
    <meta name="language" content="English">
    <meta itemprop="image" content="https://sanketbodake.ninja/myImage.jpg">
    <meta property="og:image" content="https://sanketbodake.ninja/myImage.jpg">
    <meta name="twitter:image" content="https://sanketbodake.ninja/myImage.jpg">
    <meta name="twitter:image:src" content="https://sanketbodake.ninja/myImage.jpg">
    <meta property="og:image:type" content="image/png">
    <meta property="og:image:width" content="512">
    <meta property="og:image:height" content="512">
    <meta property="twitter:image:type" content="image/png">
    <meta property="twitter:image:width" content="512">
    <meta property="twitter:image:width" content="512">
    <style>
        body {
            font-family: "Poppins", sans-serif;
            margin: 0;
            padding: 20px;
            background-color: #f4f4f4;
        }

        #code-container {
            position: relative;
            background-color: #fff;
            border: 1px solid #ccc;
            padding: 20px;
            margin-bottom: 20px;
            overflow-x: auto;
        }

        #copy-button {
            position: absolute;
            top: 10px;
            right: 10px;
            padding: 8px;
            font-size: 14px;
            background-color: #3498db;
            color: #fff;
            border: none;
            cursor: pointer;
        }
    </style>
  </head>

  <body>
    <header class="header">
      <!-- NAVBAR -->
      <nav class="navbar">
        <div class="navbar-container container">
          <div>
            <h1 class="navbar-brand">Dead Craft</h1>
          </div>
          <ul class="menu-items">
            <li><a href="#about">About</a></li>
            <li><a href="#my-works">Portfolio</a></li>
            <li><a href="#contact-me">Contact</a></li>
          </ul>
        </div>
      </nav>
      <div class="home-content" id="home-page">
      <div id="code-container">
        <!-- Place your source code here -->
        <p>// Your source code goes here</p>
        <p>function helloWorld() {</p>
        <p>    console.log('Hello, World!');</p>
        <p>}</p>
    </div>

    <button id="copy-button" onclick="copyCode()">Copy Code</button>

    <script>
        function copyCode() {
            const codeContainer = document.getElementById('code-container');
            const textArea = document.createElement('textarea');
            textArea.value = codeContainer.innerText;
            document.body.appendChild(textArea);
            textArea.select();
            document.execCommand('copy');
            document.body.removeChild(textArea);

            alert('Code copied to clipboard!');
        }
    </script>
      </body>
</html>