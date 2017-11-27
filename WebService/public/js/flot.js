
$(function() {

    var container = $("#flot-line-chart-moving");

    // Determine how many data points to keep based on the placeholder's initial size;
    // this gives us a nice high-res plot while avoiding more than one point per pixel.

    var maximum = container.outerWidth() / 2 || 300;

    //

		var totalp;
    var data = [];

		function getData(){
			var res = [];
			$.ajax({
				url:'/getData.php',
				type:'GET',
				data:{
					format:'json'
				},
				error: function(){
					alert('Cannot get data')
				},
				dataType:'json',
				success: function(json_data){
          data.shift();
          for(var i=0; i < 4; i++){
            data.push(json_data[i]);
          }
          totalp = json_data[5];
				}
			});
      console.log(totalp);
      console.log(data);
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
        data: getData(),
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
          mode: "time",
          timeformat: "%H/%M/%S",
            tickFormatter: function(v,axis) {
              var d = new Date(v);
              return d.getUTCDate() + "/" + (d.getUTCMonth() + 1);
            }
        },
        yaxis: {
            min: 0,
            max: 1000
        },
        legend: {
            show: true
        }
    });

    // Update the random dataset at 25FPS for a smoothly-animating chart

    setInterval(function updateRandom() {
        series[0].data = getData();
        plot.setData(series);
        plot.draw();
    }, 1000);

});
