import { getItem, setItem } from './storageUtils.js';

class AppointmentHandler {

  constructor(form) {
    this.form = form;
    this.messageContainer = document.getElementById('messageContainer');
    this.inputs = Array.from(form.querySelectorAll('input, textarea'));
    this.addEventListeners();
  }

  showMessage(type, message) {
    this.messageContainer.innerHTML = '';
    const div = document.createElement('div');
    div.className = `alert ${type}`;
    div.textContent = message;
    this.messageContainer.appendChild(div);

    setTimeout(() => div.remove(), 4000);
  }

  clearForm() {
    this.form.reset();
    this.inputs.forEach(i => {
      const msg = document.querySelector(`small.error[data-for="${i.name}"]`);
      if (msg) msg.textContent = '';
    });
  }

  setError(name, message) {
    const el = document.querySelector(`small.error[data-for="${name}"]`);
    if (el) el.textContent = message;
  }

  clearError(name) {
    const el = document.querySelector(`small.error[data-for="${name}"]`);
    if (el) el.textContent = '';
  }

  validateForm() {
    const name = this.form.name.value.trim();
    const email = this.form.email.value.trim();
    const phone = this.form.phone.value.replace(/\D/g, '');
    const date = this.form.date.value;
    const time = this.form.time.value;
    const cover = this.form.cover.value.trim();

    let valid = true;

    if (name.length < 3) { this.setError('name', 'Name must be at least 3 characters'); valid = false; }
    else this.clearError('name');

    const emailRe = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRe.test(email)) { this.setError('email', 'Enter valid email'); valid = false; }
    else this.clearError('email');

    if (!/^\d{10}$/.test(phone)) { this.setError('phone', 'Phone must be 10 digits'); valid = false; }
    else this.clearError('phone');

    if (!date) { this.setError('date', 'Select a date'); valid = false; }
    else this.clearError('date');

    if (!time) { this.setError('time', 'Select a time'); valid = false; }
    else this.clearError('time');

    if (date && time) {
      const dt = new Date(`${date}T${time}`);
      if (dt <= new Date()) {
        this.setError('date', 'Must be a future date/time');
        this.setError('time', 'Must be a future date/time');
        valid = false;
      }
    }

    if (cover.length < 50) { this.setError('cover', 'Comment must be 50+ characters'); valid = false; }
    else this.clearError('cover');

    if (!valid) return null;

    return {
      id: 'id' + Date.now(),
      name, email, phone, date, time, cover,
      submittedAt: new Date().toISOString()
    };
  }

  saveToLocalStorage(data) {
    const items = getItem();
    items.push(data);
    setItem(items);
  }

  handleInputEvent(e) {
    const target = e.target;
    if (!target.name) return;

    switch (target.name) {
      case 'name':
        if (target.value.trim().length >= 3) this.clearError('name');
        break;

      case 'email':
        if (/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(target.value))
          this.clearError('email');
        break;

      case 'phone':
        if (/\d{10}$/.test(target.value.replace(/\D/g, '')))
          this.clearError('phone');
        break;

      case 'cover':
        if (target.value.trim().length >= 50)
          this.clearError('cover');
        break;

      case 'date':
      case 'time':
        const d = this.form.date.value;
        const t = this.form.time.value;
        if (d && t) {
          const dt = new Date(`${d}T${t}`);
          if (dt > new Date()) {
            this.clearError('date');
            this.clearError('time');
          }
        }
        break;
    }
  }

  addEventListeners() {
    this.form.addEventListener('submit', (ev) => {
      ev.preventDefault();
      const data = this.validateForm();

      if (data) {
        this.saveToLocalStorage(data);
        this.showMessage('success', 'Application submitted successfully');
        this.clearForm();
      } else {
        this.showMessage('error', 'Please fix the errors and try again');
      }
    });

    this.form.addEventListener('input', (e) => this.handleInputEvent(e));
    this.form.addEventListener('blur', (e) => this.handleInputEvent(e), true);
  }
}

// Initialize
const form = document.getElementById('appointmentForm');
new AppointmentHandler(form);
