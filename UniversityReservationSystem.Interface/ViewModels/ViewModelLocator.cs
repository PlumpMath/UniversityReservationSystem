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
            SimpleIoc.Default.Register<StudentsVM>();
            SimpleIoc.Default.Register<TeachersVM>();
            SimpleIoc.Default.Register<ReservationsVM>();
            SimpleIoc.Default.Register<RoomsVM>();
        }

        public static GroupsVM Groups
        {
            get
            {
                return ServiceLocator.Current.GetInstance<GroupsVM>();
            }
        }

        public static StudentsVM Students
        {
            get
            {
                return ServiceLocator.Current.GetInstance<StudentsVM>();
            }
        }

        public static TeachersVM Teachers
        {
            get
            {
                return ServiceLocator.Current.GetInstance<TeachersVM>();
            }
        }

        public static ReservationsVM Reservations
        {
            get
            {
                return ServiceLocator.Current.GetInstance<ReservationsVM>();
            }
        }

        public static RoomsVM Rooms
        {
            get
            {
                return ServiceLocator.Current.GetInstance<RoomsVM>();
            }
        }
        
        public static void Cleanup()
        {
        }
    }
}