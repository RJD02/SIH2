import "./App.css";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import Record from "./components/Record";
import Graph from "./pages/Visual/Graph";
import Map from "./pages/Visual/map/Map";

function App() {
  // MQ2, DHT, Level
  return (
    <div className="App">
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Record />} />
          <Route path="/visual" element={<Graph />} />
          <Route path="/map" element={<Map />} />
        </Routes>
      </BrowserRouter>
    </div>
  );
}

export default App;
