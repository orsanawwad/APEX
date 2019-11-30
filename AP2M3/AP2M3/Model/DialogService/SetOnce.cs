using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model.DialogService
{
    /// <summary>
    /// Set once single variable container where setting twice throws and error
    /// Useful to prevent stuff from getting overwritten.
    /// </summary>
    /// <typeparam name="T">Generic type for setting once.</typeparam>
    public class SetOnce<T>
    {
        private bool set;
        private T value;

        public T Value
        {
            get { return value; }
            set
            {
                if (set) throw new InvalidOperationException("The value \"" + value.ToString() + "\" has already been set.");
                set = true;
                this.value = value;
            }
        }

        public static implicit operator T(SetOnce<T> toConvert)
        {
            return toConvert.value;
        }
    }
}
