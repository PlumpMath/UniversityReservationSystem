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

        private bool _addingModeActive;

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

        public bool AddingModeActive
        {
            get { return _addingModeActive; }
            set
            {
                if (_addingModeActive != value)
                {
                    _addingModeActive = value;
                    RaisePropertyChanged("AddingModeActive");
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
            AddingModeActive = true;

            Name = "Type Room Name";
            Capacity = 0;
            NumOfComputers = 0;
            NumOfChairs = 0;
            NumOfTables = 0;
            AdditionalEquipment = "Type additional equipment";
        }

        protected override void SaveChanges()
        {
            if (AddingModeActive)
            {
                // adding mode

                if (Type == RoomType.Exercise)
                    Rooms.Add(new ExerciseRoom(Name, Capacity, NumOfChairs, NumOfTables));
                else
                    Rooms.Add(new LabRoom(Name, Capacity, AdditionalEquipment, NumOfComputers));

                SelectedItem = Rooms.Last();
                AddingModeActive = false;
            }
            else
            {
                // editing mode

                if (Type == RoomType.Exercise)
                    ((ExerciseRoom)SelectedItem).Edit(Name, Capacity, NumOfChairs, NumOfTables);
                else
                    ((LabRoom)SelectedItem).Edit(Name, Capacity, AdditionalEquipment, NumOfComputers);
            }
        }

        protected override void Delete()
        {
            if (AddingModeActive)
            {
                SelectedItem = null;
                SelectedItem = Rooms.FirstOrDefault();
                AddingModeActive = false;
            }
            else
            {
                SelectedItem.Delete();
                Rooms.Remove(SelectedItem);
                SelectedItem = Rooms.FirstOrDefault();
            }
        }

        protected override sealed void UpdateAfterSelection(bool isNull)
        {
            AddingModeActive = false;

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
                    NumOfChairs = ((ExerciseRoom)SelectedItem).NumOfChairs;
                    NumOfTables = ((ExerciseRoom)SelectedItem).NumOfTables;
                }
                else
                {
                    NumOfComputers = ((LabRoom)SelectedItem).NumOfComputers;
                    AdditionalEquipment = ((LabRoom)SelectedItem).AdditionalEquipment;
                }

                Name = SelectedItem.Name;
                Type = roomType;
                Capacity = SelectedItem.Capacity;
            }
            else
            {
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
