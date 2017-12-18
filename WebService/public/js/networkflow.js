$(function() {

    var container = $("#networkFlow");

    // Determine how many data points to keep based on the placeholder's initial size;
    // this gives us a nice high-res plot while avoiding more than one point per pixel.

    var maximum = container.outerWidth() / 2 || 300;

    //

    var data = [];
    var test = [];
    var maxTest = 100;

    function getData(){
        if(data.length){
            data = data.slice(1);
        }
        $.ajax({
            url:"/getData.php",
            type: "get",
            dataType: "json",
            success: function(response){
                test.push(response[0]);
                maxTest = parseInt(response[1]);
                document.getElementById("ipaddressId").innerHTML = response[5];
                document.getElementById("ifnameId").innerHTML = response[6];
                document.getElementById("httpCount").innerHTML = response[2];
                document.getElementById("httpsCount").innerHTML = response[3];
                document.getElementById("dnsCount").innerHTML = response[4];
                if(response[7] > 0){
                    $("#blue-modal").modal();
                    document.getElementById("attackerIp").innerHTML = response[9];
                    //alert("Under attack : " + response[9]);
                    document.getElementById("attackCountId").innerHTML = response[8];
                }
            }
        });
        var res = [];
        for (var i = 0; i < data.length; ++i){
            res.push([i, test[i]])
        }
        console.log(maxTest);
        return res;
    }

    function getRandomData() {

        if (data.length) {
            data = data.slice(1);
        }

        while (data.length < maximum) {
            var previous = data.length ? data[data.length - 1] : 50;
            var y = previous + Math.random() * 10 - 5;
            data.push(y < 0 ? 0 : y > 100 ? 100 : y);
        }

        // zip the generated y values with the x values

        var res = [];
        for (var i = 0; i < data.length; ++i) {
            res.push([i, data[i]])
        }

        return res;
    }

    //

    series = [{
        data: getRandomData(),
        lines: {
            fill: true
        }
    }];

    //

    var plot = $.plot(container, series, {
        grid: {
            borderWidth: 1,
            minBorderMargin: 20,
            labelMargin: 10,
            backgroundColor: {
                colors: ["#fff", "#e4f4f4"]
            },
            margin: {
                top: 8,
                bottom: 20,
                left: 20
            },
            markings: function(axes) {
                var markings = [];
                var xaxis = axes.xaxis;
                for (var x = Math.floor(xaxis.min); x < xaxis.max; x += xaxis.tickSize * 2) {
                    markings.push({
                        xaxis: {
                            from: x,
                            to: x + xaxis.tickSize
                        },
                        color: "rgba(232, 232, 255, 0.2)"
                    });
                }
                return markings;
            }
        },
        xaxis: {
            tickFormatter: function() {
                return "";
            }
        },
        yaxis: {
            min: 0,
            max: 100
        },
        legend: {
            show: true
        }
    });
    console.log(maxTest)

    // Update the random dataset at 25FPS for a smoothly-animating chart

    setInterval(function updateRandom() {
        var axes = plot.getAxes();
        axes.yaxis.options.max = maxTest;
        series[0].data = getData();
        plot.setData(series);
        plot.setupGrid();
        plot.draw();
    }, 1000);

});
