using System;
using System.Linq;
using System.Windows.Markup;

namespace UniversityReservationSystem.Interface.Helpers
{
    /// <summary>
    /// Converts enum to item source for combobox etc...
    /// </summary>
    public class EnumToItemsSource : MarkupExtension
    {
        /// <summary>
        /// holds enum type
        /// </summary>
        private readonly Type _type;

        /// <summary>
        /// Initializes a new instance of the <see cref="EnumToItemsSource"/> class.
        /// </summary>
        /// <param name="type">The enum type.</param>
        public EnumToItemsSource(Type type)
        {
            _type = type;
        }

        /// <summary>
        /// When implemented in a derived class, returns an object that is provided as the value of the target property for this markup extension.
        /// </summary>
        /// <param name="serviceProvider">A service provider helper that can provide services for the markup extension.</param>
        /// <returns>
        /// The object value to set on the property where the extension is applied.
        /// </returns>
        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return Enum.GetValues(_type)
                .Cast<object>()
                .Select(e => new { Value = (int)e, DisplayName = e.ToString() });
        }
    }
}
