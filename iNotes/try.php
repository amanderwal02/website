<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Source Code Viewer</title>
    <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap">
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
