import axios from "axios";
const g = 9.81;
const b = 1.5;
const slope = 3; //
const slopeOfPipe = 0.001;
const lengthBetweenManhole = 20; // meters
const inchToMeter = 0.0254;
const firstLevel = 4;
export const getRecords = async () => {
  try {
    let data = await axios.get("https://young-dawn-87102.herokuapp.com/record");
    data = await data.data;
    const records = data.records;
    records.reverse();
    const res = [];
    const today = new Date().toISOString().substring(0, 10);
    console.log("Today", today);
    const recordsData = [];
    for (let i = 0; i < records.length; i++) {
      const recordDate = records[i].time.toString().substring(0, 10);
      console.log(recordDate);
      const level = firstLevel - records[i].level * inchToMeter;
      const a = b - (2 * level) / slope;
      const A = ((a + b) * level) / 2;
      const z = slopeOfPipe * lengthBetweenManhole;
      const v = Math.sqrt((level - z) * 2 * g);
      const q = v * A;
      records[i].velocity = v;
      records[i].discharge = q;
      records[i].area = A;
      // records[i].
      console.log("Area", A, "Discharge", q);
      if (recordDate === today) res.push(records[i]);
    }
    console.log(res);
    return res;
  } catch (err) {
    console.log(err);
    return [];
  }
};
//
