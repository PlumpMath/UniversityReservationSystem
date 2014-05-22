using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public enum RoomType
    {
        Lab,
        Exercise,
    };

    public class RoomsVM : IReservableViewModel<IRoom>
    {
        private string _name;
        private RoomType _type;
        private int _capacity;
        private bool _isNameFocused;
        private int _numOfComputers;
        private int _numOfTables;
        private int _numOfChairs;
        private string _additionalEquipment;

        private bool _labFieldsVisible;
        private bool _exFieldsVisible;

        public ObservableCollection<IRoom> Rooms { get; set; }

        public bool IsNameFocused
        {
            get { return _isNameFocused; }
            set
            {
                if (_isNameFocused != value)
                {
                    _isNameFocused = value;
                    RaisePropertyChanged("IsNameFocused");
                }
            }
        }
        public string Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    RaisePropertyChanged("Name");
                }
            }
        }
        public RoomType Type
        {
            get { return _type; }
            set
            {
                if (_type != value)
                {
                    _type = value;
                    RaisePropertyChanged("Type");
                }
            }
        }
        public int Capacity
        {
            get { return _capacity; }
            set
            {
                if (_capacity != value)
                {
                    _capacity = value;
                    RaisePropertyChanged("Capacity");
                }
            }
        }
        public int NumOfComputers
        {
            get { return _numOfComputers; }
            set
            {
                if (_numOfComputers != value)
                {
                    _numOfComputers = value;
                    RaisePropertyChanged("NumOfComputers");
                }
            }
        }
        public int NumOfTables
        {
            get { return _numOfTables; }
            set
            {
                if (_numOfTables != value)
                {
                    _numOfTables = value;
                    RaisePropertyChanged("NumOfTables");
                }
            }
        }
        public int NumOfChairs
        {
            get { return _numOfChairs; }
            set
            {
                if (_numOfChairs != value)
                {
                    _numOfChairs = value;
                    RaisePropertyChanged("NumOfChairs");
                }
            }
        }
        public string AdditionalEquipment
        {
            get { return _additionalEquipment; }
            set
            {
                if (_additionalEquipment != value)
                {
                    _additionalEquipment = value;
                    RaisePropertyChanged("AdditionalEquipment");
                }
            }
        }

        public bool LabFieldsVisible
        {
            get { return _labFieldsVisible; }
            set
            {
                if (_labFieldsVisible != value)
                {
                    _labFieldsVisible = value;
                    RaisePropertyChanged("LabFieldsVisible");
                }
            }
        }
        public bool ExFieldsVisible
        {
            get { return _exFieldsVisible; }
            set
            {
                if (_exFieldsVisible != value)
                {
                    _exFieldsVisible = value;
                    RaisePropertyChanged("ExFieldsVisible");
                }
            }
        }

        public RoomsVM()
        {
            if (IsInDesignMode) return;

            Rooms = App.Rooms;
            SelectedItem = Rooms.FirstOrDefault();

            UpdateAfterSelection(false);
        }

        protected override void Add()
        {
            throw new System.NotImplementedException();
        }

        protected override void SaveChanges()
        {
            throw new System.NotImplementedException();
        }

        protected override void Delete()
        {
            throw new System.NotImplementedException();
        }

        protected override sealed void UpdateAfterSelection(bool isNull)
        {
            if (!isNull)
            {
                if (ReservationsOfSelected != null)
                {
                    SelectedItem.GetReservations(ReservationsOfSelected);
                    MonthChanged(_currentDateOnCalendar);
                }

                RoomType roomType;

                if(!Enum.TryParse(SelectedItem.Type, true, out roomType))
                    throw new Exception("Error while parsing the enum!");

                if (roomType == RoomType.Exercise)
                {
                    LabFieldsVisible = false;
                    ExFieldsVisible = true;

                    NumOfChairs = ((ExerciseRoom)SelectedItem).NumOfChairs;
                    NumOfTables = ((ExerciseRoom)SelectedItem).NumOfTables;
                }
                else
                {
                    ExFieldsVisible = false;
                    LabFieldsVisible = true;

                    NumOfComputers = ((LabRoom)SelectedItem).NumOfComputers;
                    AdditionalEquipment = ((LabRoom)SelectedItem).AdditionalEquipment;
                }

                Name = SelectedItem.Name;
                Type = roomType;
                Capacity = SelectedItem.Capacity;
            }
            else
            {
                LabFieldsVisible = false;
                ExFieldsVisible = false;

                Name = String.Empty;
                Type = 0;
                Capacity = 0;
                ReservationsOfSelected.Clear();
                ReservationsOfSelectedOnCalendar.Clear();
            }
        }

        public void ReservationClicked(IntPtr reservationptr)
        {
            MessageBox.Show(App.Reservations.Single(x => x.Ptr == reservationptr).ToString());
        }
    }
}
