using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Animation;
using System.Windows.Media.Media3D;

namespace SimulationTool
{
    public class FileModel
    {
        OutputManager outManger;
        public FileModel(OutputManager outMan)
        {
            outManger = outMan;
            Read = true;
        }

        public bool Read { get; set; }
        public int ReadPosition { get; set; }

        public string[] Content { get; set; }
        List<double> timelist = new List<double>();
        List<int> targElement = new List<int>();
      
        public double CurrentTime { get { return timelist[ReadPosition]; } }
        public double TSpan { get { return timelist[ReadPosition + 1] - timelist[ReadPosition + 1]; } }

        Dictionary<int, List<KeyValuePair<double, Point3D>>> data = new Dictionary<int, List<KeyValuePair<double, Point3D>>>();

        List<Point3D> toDisplay = new List<Point3D>();
        public List<Point3D> CurrentLoc
        {
            get
            {
                toDisplay.Clear();
                foreach (var elmnt in data) { toDisplay.Add(elmnt.Value[ReadPosition].Value); }
                return toDisplay;
            }
        }

        public void select(String fpath)
        {
            List<double> CurrentLine;
            Content = System.IO.File.ReadAllLines(fpath);

            for (int i = 1; i < Content.Length; i++)
            {
                CurrentLine = Content[i].Split(' ').Select(x => Double.Parse(x, NumberStyles.Any, CultureInfo.InvariantCulture)).ToList();
                //  timelist.Add(CurrentLine[0]);
                KeyValuePair<double, Point3D> location = new KeyValuePair<double, Point3D>(CurrentLine[0], new Point3D(CurrentLine[2], CurrentLine[3], CurrentLine[4]));
                int elemnt = Convert.ToInt32(CurrentLine[1]);
                if (!data.ContainsKey(elemnt))
                {
                    List<KeyValuePair<double, Point3D>> locL = new List<KeyValuePair<double, Point3D>>();
                    data.Add(elemnt, locL);
                }
                data[elemnt].Add(location);

                //                targElement.Add( Convert.ToInt32( CurrentLine[1]));
                //locList.Add(new Point3D(CurrentLine[2], CurrentLine[3], CurrentLine[4]));
            }
            ReadPosition = 0;
        }

        public void next()
        {
            if (!Read) { return; }
            ReadPosition++;
            if (ReadPosition >= data[0].Count - 1) { Read = false; }
        }

        public void FilterFile(double step)
        {
            for (int index = 0; index < data.Count; index++)
            {
                var dat = data[index];
                List<KeyValuePair<double, Point3D>> newLocList = new List<KeyValuePair<double, Point3D>>();
                double t = step;
                dat.Sort((x, y) => x.Key.CompareTo(y.Key));
                int i = 1;
                while (i < dat.Count - 1)
                {
                    while (t < dat[i].Key)
                    {
                        var slope = Point3D.Subtract(dat[i].Value, dat[i - 1].Value);
                        Vector3D.Divide(slope, (dat[i].Key - dat[i - 1].Key));
                        Vector3D.Multiply(slope, t - dat[i - 1].Key);
                        newLocList.Add(new KeyValuePair<double, Point3D>(t, Point3D.Add(dat[i - 1].Value, slope)));
                        t += step;
                    }
                    if (t == dat[i].Key)
                    {
                        newLocList.Add(new KeyValuePair<double, Point3D>(t, dat[i].Value));
                        t += step;
                    }
                    if (t > dat[i].Key) { i++; }
                }
                data[index] = newLocList;
            }
        }

        public void FormatCoord(double Wdth, double Hght, double radius)
        {
            double xdiff = Wdth * 0.5 - radius;
            double ydiff = Hght * 0.5 - radius;

            for (int index = 0; index < data.Count; index++)
            {
                var dat = data[index];
                List<KeyValuePair<double, Point3D>> newLocList = new List<KeyValuePair<double, Point3D>>();
                foreach (var loc in dat)
                {
                    newLocList.Add(new KeyValuePair<double, Point3D>(loc.Key, new Point3D(loc.Value.X + xdiff, loc.Value.Y + ydiff, loc.Value.Z)));
                }
                data[index] = newLocList;
            }
        }

    }
}
