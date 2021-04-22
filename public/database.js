const r1 = document.getElementById('r1');
const r2 = document.getElementById('r2');

const r1t1 = document.getElementById('r1t1');
const r2t1 = document.getElementById('r2t1');
const r1s1 = document.getElementById('r1s1');
const r2s1 = document.getElementById('r2s1');

const r1t2 = document.getElementById('r1t2');
const r2t2 = document.getElementById('r2t2');
const r1s2 = document.getElementById('r1s2');
const r2s2 = document.getElementById('r2s2');

const r1t3 = document.getElementById('r1t3');
const r2t3 = document.getElementById('r2t3');
const r1s3 = document.getElementById('r1s3');
const r2s3 = document.getElementById('r2s3');

const result = document.getElementById('result');

const database = firebase.database();
const rootRef = database.ref('IMU_LSM6DS3');


rootRef.on('value', snapshot => {
  data = snapshot.val();
  console.log(data);
  //Car 1 Data
  var c1cp1s = data["1-car1Stats"]["cp1s"];
  var c1cp1t = data["1-car1Stats"]["cp1t"];
  var c1cp2s = data["1-car1Stats"]["cp2s"];
  var c1cp2t = data["1-car1Stats"]["cp2t"];
  var c1cp3s = data["1-car1Stats"]["cp3s"];
  var c1cp3t = data["1-car1Stats"]["cp3t"];

  //Car 2 Data
  var c2cp1s = data["2-car2Stats"]["cp1s"];
  var c2cp1t = data["2-car2Stats"]["cp1t"];
  var c2cp2s = data["2-car2Stats"]["cp2s"];
  var c2cp2t = data["2-car2Stats"]["cp2t"];
  var c2cp3s = data["2-car2Stats"]["cp3s"];
  var c2cp3t = data["2-car2Stats"]["cp3t"];

  //Update Values
  r1t1.innerText = c1cp1t + " seconds";
  r2t1.innerText = c2cp1t + " seconds";
  r1s1.innerText = c1cp1s + " ft/second";
  r2s1.innerText = c2cp1s + " ft/second";
  r1t2.innerText = c1cp2t + " seconds";
  r2t2.innerText = c2cp2t + " seconds";
  r1s2.innerText = c1cp2s + " ft/second";
  r2s2.innerText = c2cp2s + " ft/second";
  r1t3.innerText = c1cp3t + " seconds";
  r2t3.innerText = c2cp3t + " seconds";
  r1s3.innerText = c1cp3s + " ft/second";
  r2s3.innerText = c2cp3s + " ft/second";

  if (c1cp3t < c2cp3t){

    var n = (c2cp3t - c1cp3t).toFixed(5);

    result.innerText = "Racer #1 wins by " + n + " seconds!";

    r1t3.style.backgroundColor = "green";
    r1t3.style.color = "white";
    r2t3.style.backgroundColor = "red";
    r2t3.style.color = "white";

  }
  else{

    var n = (c1cp3t - c2cp3t).toFixed(5);

    result.innerText = "Racer #2 wins by " + n + " seconds!";

    r1t3.style.backgroundColor = "red";
    r1t3.style.color = "white";
    r2t3.style.backgroundColor = "green";
    r2t3.style.color = "white";

  }

  

})

