const char html[] = R"=====(
<!DOCTYPE HTML><html><head><title>Last Example</title>
<style id="CSSstyle" data-color="#f8be00">body{margin:0;padding:0;display:flex;flex-direction:column;justify-content:center;align-items:center;min-height:100vh;}.header{background-color:#ffe600;font-family:emoji;display:flex;flex-direction:column;align-items:center;justify-content:space-between;padding:30px;z-index:2;height:200px;margin-bottom:30px;}.body{height:400px;background-color:white;z-index:2;width:300px;border-radius:40px 40px 0 0;display:flex;flex-direction:column;justify-content:center;align-items:center;}.controlBtn{outline-style:none;border-radius:10px;width:180px;height:30px;background-color:white;}.progressBox{width:100%;height:30px;border-radius:10px;overflow:hidden;position:relative;}.progressBar{position:absolute;height:100%;background-color:#f8be00;width:0;}.progressContainer{width:100%;height:100%;z-index:21;background-color:#343934393439;} .hide { position:absolute; top:-1px; left:-1px; width:1px; height:1px; }</style>
</head>
<body><script>
function changeRelayState(){httpRequest1=new XMLHttpRequest(); httpRequest1.open("GET",stateChange,true);httpRequest1.onreadystatechange=res_handle;httpRequest1.send();}</script> 
<form action="/review1" method="POST" target="hiddenFrame"><div><label for="say">Who do you want to say it to?</label><input name="to" id="to"></div><div><button>Set Timer</button></div></form></div> 
<form action="/review2" method="POST" target="hiddenFrame"><div><label for="to">Please enter the Timer 1 value</label><input name="say" id="say"></div><div><button>Set Timer</button></div></form></div> 
</body></html>
)=====";
