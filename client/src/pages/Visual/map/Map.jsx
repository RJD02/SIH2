import React from "react";
import { useEffect } from "react";
import { useState } from "react";
import { axios } from "axios";
import { MapContainer, Popup, TileLayer, Marker } from "react-leaflet";
import "./Map.css";
import "leaflet/dist/leaflet.css";
function Map() {
  const [record, setRecord] = useState({});
  const [latitude, setLatitude] = useState(0);
  const [longitude, setLongitude] = useState(0);
  useEffect(() => {
    const getNode = async () => {
      const { data } = await axios.get(
        "https://young-dawn-87102.herokuapp.com/record"
      );
      //   const data = { records: [], longitude, latitude };
      if (data.records === null) setRecord({});
      setRecord(data.records);
      setLongitude(75.894577);
      setLatitude(27.031566);
    };
    getNode();
  }, []);
  return (
    <MapContainer center={[longitude, latitude]} zoom={13}>
      <TileLayer
        attribution='&copy; <a href="http://
        osm.org/copyright">OpenStreetMap</a> contributors'
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />{" "}
      <Marker position={[longitude, latitude]}>
        <Popup>
          {record !== null && (
            <ul>
              <li>{record.level}</li>
              {record.MQ2}
              <li></li>
            </ul>
          )}
        </Popup>
      </Marker>
    </MapContainer>
  );
}

export default Map;
