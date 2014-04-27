using GalaSoft.MvvmLight.Ioc;
using Microsoft.Practices.ServiceLocation;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class ViewModelLocator
    {
        public ViewModelLocator()
        {
            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);

            SimpleIoc.Default.Register<GroupsVM>();
        }

        public static GroupsVM Groups
        {
            get
            {
                return ServiceLocator.Current.GetInstance<GroupsVM>();
            }
        }
        
        public static void Cleanup()
        {
        }
    }
}