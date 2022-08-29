import moment from "moment";
import React from "react";
import { useEffect } from "react";
import { useState } from "react";
import { getRecords } from "../../api/getRecords";
import LineChart from "./LineChart";
import { Line } from "react-chartjs-2";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Chart } from "react-chartjs-2";
import "./LineChart.css";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

function Graph() {
  const [data, setData] = useState([]);
  const [xAxisValues, setXAxisValues] = useState([]);
  const [levelValues, setLevelValues] = useState([]);
  const [mq2Values, setMq2Values] = useState([]);
  const [velocityValues, setVelocityValues] = useState([]);
  const [dischargeValues, setDischargeValues] = useState([]);

  useEffect(() => {
    let isMounted = true;
    const setServerData = async () => {
      const data = await getRecords();
      console.log(data);
      //   console.log(data.map((ele) => ele.MQ2));
      data.reverse();
      if (isMounted) {
        setData(data);
        setXAxisValues(data.map((ele) => moment(ele.time)));
        setLevelValues(data.map((ele) => ele.level));
        setMq2Values(data.map((ele) => ele.MQ2));
        setVelocityValues(data.map((ele) => ele.velocity));
        setDischargeValues(data.map((ele) => ele.discharge));
      }
    };
    setServerData();
    return () => {
      isMounted = false;
    };
  }, []);

  const options = {
    labels: xAxisValues,
    datasets: [
      {
        label: "Level values",
        data: levelValues,
        fill: true,
        backgroundColor: "#3a86ff",
        borderColor: "#ffbe0b",
        responsive: true,
      },
      {
        label: "MQ5 values",
        data: mq2Values,
        fill: false,
        backgroundColor: "#a8dadc",
        borderColor: "#e63946",
        responsive: true,
      },
      {
        label: "Velocity",
        data: velocityValues,
        fill: false,
        responsive: true,
      },
      // {
      //   label: "Humidity Values",
      //   data: humidityValues,
      //   fill: false,
      //   backgroundColor: "#f4a261",
      //   borderColor: "#e76f51",
      //   responsive: true,
      // },
      // {
      //   label: "Temperature Values",
      //   data: temperatureValues,
      //   fill: false,
      //   backgroundColor: "#588157",
      //   borderColor: "#dad7cd",
      //   responsive: true,
      // },
    ],
  };

  return (
    <div>
      <h3 className="mb-2 mt-1">Mixed Graph</h3>
      <Line data={options} />
      <h3 className="mb-2 mt-1">Levels Graph</h3>
      <LineChart xAxis={xAxisValues} yAxis={levelValues} label="Levels" />
      <h3 className="mb-2 mt-1">MQ2 Graph</h3>
      <LineChart xAxis={xAxisValues} yAxis={mq2Values} label="mq2" />
      <h3 className="mb-2 mt-1">Velocity Graph</h3>
      <LineChart xAxis={xAxisValues} yAxis={velocityValues} label="Velocity" />
      <h3 className="mb-2 mt-1">Discharge Graph</h3>
      <LineChart
        xAxis={xAxisValues}
        yAxis={dischargeValues}
        label="Discharge"
      />
    </div>
  );
}

export default Graph;
