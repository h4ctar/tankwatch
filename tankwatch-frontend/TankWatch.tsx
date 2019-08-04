import * as React from 'react';
import Axios from "axios";
import { Line } from 'react-chartjs-2';

export default function TankWatch() {
    const [humidityData, setHumidityData] = React.useState();
    const [temperatureData, setTemperatureData] = React.useState();

    React.useEffect(() => {
        Axios.get("https://836uvpia6g.execute-api.ap-southeast-2.amazonaws.com/default/queryTankReading")
            .then((result) => {
                const humidity = result.data.Items
                    .map((item) => { return { t: new Date(item.published_at), y: item.humidity }; })
                    .sort((a, b) => a.t - b.t);
                const temperature = result.data.Items
                    .map((item) => { return { t: new Date(item.published_at), y: item.temperature }; })
                    .sort((a, b) => a.t - b.t);

                setHumidityData({
                    datasets: [
                        {
                            label: 'Humidity',
                            fill: false,
                            lineTension: 0,
                            data: humidity
                        }
                    ]
                });

                setTemperatureData({
                    datasets: [
                        {
                            label: 'Temperature',
                            fill: false,
                            lineTension: 0,
                            data: temperature
                        }
                    ]
                });
            });
    }, []);

    return (
        <div>
            {humidityData && <Line data={humidityData} options={{ scales: { xAxes: [{ type: "time" }] } }} />}
            {temperatureData && <Line data={temperatureData} options={{ scales: { xAxes: [{ type: "time" }] } }} />}
        </div>
    );
}
