using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public abstract class IViewModel<T> : ViewModelBase
        where T: class
    {
        private T _selectedItem;
        public T SelectedItem
        {
            get { return _selectedItem; }
            set
            {
                if (_selectedItem != value)
                {
                    _selectedItem = value;
                    UpdateAfterSelection(value == null);
                    RaisePropertyChanged("SelectedItem");
                }
            }
        }

        protected IViewModel()
        {
            InitializeCommands();
        }

        private void InitializeCommands()
        {
            AddCommand = new RelayCommand(Add);
            SaveChangesCommand = new RelayCommand(SaveChanges);
            DeleteCommand = new RelayCommand(Delete);
        }

        protected abstract void Add();
        protected abstract void SaveChanges();
        protected abstract void Delete();
        protected abstract void UpdateAfterSelection(bool isNull);

        public RelayCommand AddCommand { get; private set; }
        public RelayCommand SaveChangesCommand { get; private set; }
        public RelayCommand DeleteCommand { get; private set; }
    }
}
